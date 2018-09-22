let component = ReasonReact.statelessComponent("Cell");

let make = (~data, _children) => {
  ...component,
  render: _self => {
    let rec parseHex =
            (hex: list(int)): (ReasonReact.reactElement, list(int)) => {
      let key = List.length(hex)->string_of_int;
      switch (hex) {
      | [] => (ReasonReact.null, [])
      | [a, ...rest] =>
        switch (a) {
        /* NIL */
        | 0xc0 => (<Block header="Nil" raw=[a] color="#FAA" key />, rest)

        /* BOOLEANS */
        | 0xc2 => (<Block header="false" raw=[a] color="#AAF" key />, rest)

        | 0xc3 => (<Block header="true" raw=[a] color="#AAF" key />, rest)

        /* INTEGERS */
        | _ when a < 0b10000000 =>
          /* positive 7 bit int */
          let num =
            try (Printf.sprintf("0x%02X", a)->int_of_string) {
            | _ => 0
            };
          (<Block header=num->string_of_int raw=[a] key />, rest);

        | _ when a >= 0b11100000 =>
          /* negative 5 bit int */
          let num =
            (
              try (Printf.sprintf("0x%02X", a)->int_of_string) {
              | _ => 0
              }
            )
            - 256;
          (<Block header=num->string_of_int raw=[a] key />, rest);

        | 0xcc =>
          /* uint 8 */
          let head = List.hd(rest);
          let tail = List.tl(rest);
          let num = head->string_of_int;
          (<MPInt header="uint 8" headerRaw=a raw=[head] num key />, tail);

        | 0xcd =>
          /* uint 16 */
          let (raw, tail) = Util.splitAt(rest, 2);
          let num = Util.hex_of_int_list(raw)->int_of_string->string_of_int;
          (<MPInt header="uint 16" headerRaw=a raw num key />, tail);

        | 0xce =>
          /* uint 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          let num = Util.hex_of_int_list(raw)->int_of_string->string_of_int;
          (<MPInt header="uint 32" headerRaw=a raw num key />, tail);

        | 0xcf =>
          /* uint 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num =
            Util.hex_of_int_list(raw)->Int64.of_string->Int64.to_string;
          (<MPInt header="uint 64" headerRaw=a raw num key />, tail);

        | 0xd0 =>
          /* int 8 */
          let head = List.hd(rest);
          let tail = List.tl(rest);
          let num = head->Int64.of_int->Util.addSign(8);
          (<MPInt header="uint 8" headerRaw=a raw=[head] num key />, tail);

        | 0xd1 =>
          /* uint 16 */
          let (raw, tail) = Util.splitAt(rest, 2);
          let num =
            Util.hex_of_int_list(raw)->Int64.of_string->Util.addSign(16);
          (<MPInt header="int 16" headerRaw=a raw num key />, tail);

        | 0xd2 =>
          /* int 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          let num =
            Util.hex_of_int_list(raw)->Int64.of_string->Util.addSign(32);
          (<MPInt header="int 32" headerRaw=a raw num key />, tail);

        | 0xd3 =>
          /* uint 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num =
            Util.hex_of_int_list(raw)->Int64.of_string->Util.addSign(64);
          (<MPInt header="int 64" headerRaw=a raw num key />, tail);

        /* FLOATS (doesn't work) */
        | 0xca =>
          /* Float 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          let num = Util.hex_of_int_list(raw)->float_of_string;
          (<MPFloat header=a raw num key />, tail);

        | 0xcb =>
          /* Float 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num = Util.hex_of_int_list(raw)->float_of_string;
          (<MPFloat header=a raw num key />, tail);

        /* STRINGS */
        | _ when a >= 0xA0 && a <= 0xBF =>
          /* 1 Byte String Header */
          let mask = 0b00011111->Int32.of_int;
          let len = Int32.of_int(a)->Int32.logand(mask)->Int32.to_int;
          let (strContent, tail) = Util.splitAt(rest, len);
          (<MPString header=[a] len strContent key />, tail);

        | 0xd9 =>
          /* 2 Byte String Header */
          let head = List.hd(rest);
          let len = head;
          let (strContent, tail) = Util.splitAt(List.tl(rest), len);
          (<MPString header=[a, head] len strContent key />, tail);

        | 0xda =>
          /* 2 Byte String Header */
          let (head, rest) = Util.splitAt(rest, 2);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let (strContent, tail) = Util.splitAt(rest, len);
          (<MPString header=[a, ...head] len strContent key />, tail);

        | 0xdb =>
          /* 4 Byte String Header */
          let (head, rest) = Util.splitAt(rest, 4);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let (strContent, tail) = Util.splitAt(rest, len);
          (<MPString header=[a, ...head] len strContent key />, tail);

        /* Binary */
        | 0xc4 =>
          /* 1 Byte Binary Header */
          let len = List.hd(rest);
          let rest = List.tl(rest);
          let (binContent, tail) = Util.splitAt(rest, len);
          (<MPBinary header=[len] binContent len key />, tail);

        | 0xc5 =>
          /* 2 Byte Binary Header */
          let (head, rest) = Util.splitAt(rest, 2);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let (binContent, tail) = Util.splitAt(rest, len);
          (<MPBinary header=head binContent len key />, tail);

        | 0xc6 =>
          /* 4 Byte Binary Header */
          let (head, rest) = Util.splitAt(rest, 4);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let (binContent, tail) = Util.splitAt(rest, len);
          (<MPBinary header=head binContent len key />, tail);

        /* Array */
        | _ when a >= 0b10010000 && a <= 0b10011111 =>
          /* 1 Byte Array Header */
          let mask = 0b00001111->Int32.of_int;
          let len = Int32.of_int(a)->Int32.logand(mask)->Int32.to_int;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let arrContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPArray header=[a] len arrContent key />, rest);

        | 0xdc =>
          /* 2 Byte Array Header */
          let (head, rest) = Util.splitAt(rest, 2);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let arrContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPArray header=[a] len arrContent key />, rest);

        | 0xdd =>
          /* 4 Byte Array Header */
          let (head, rest) = Util.splitAt(rest, 4);
          let len = Util.hex_of_int_list(head)->int_of_string;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let arrContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPArray header=[a] len arrContent key />, rest);

        /* Map */
        | _ when a >= 0b10000000 && a <= 0b10001111 =>
          /* Included Map Header */
          /* 1 Byte Array Header */
          let mask = 0b00001111->Int32.of_int;
          let len = Int32.of_int(a)->Int32.logand(mask)->Int32.to_int * 2;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let mapContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPMap header=[a] len mapContent key />, rest);

        | 0xde =>
          /* 2 Byte Map Header */
          let (head, rest) = Util.splitAt(rest, 2);
          let len = Util.hex_of_int_list(head)->int_of_string * 2;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let mapContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPMap header=[a] len mapContent key />, rest);

        | 0xdf =>
          /* 4 Byte Map Header */
          let (head, rest) = Util.splitAt(rest, 4);
          let len = Util.hex_of_int_list(head)->int_of_string * 2;
          let tupleContent = Array.make(len, (ReasonReact.null, []));
          for (i in 0 to len - 1) {
            let (_, rest) =
              try (tupleContent[i - 1]) {
              | _ => (ReasonReact.null, rest)
              };
            tupleContent[i] = parseHex(rest);
          };
          let mapContent = Array.map(((e, _)) => e, tupleContent);
          let (_, rest) = tupleContent[len - 1];
          (<MPMap header=[a] len mapContent key />, rest);

        /* Unimplemented */
        /* Maybe throw error and use componentDidCatch to display msg */
        /* Or maybe return unimplemented component */
        /* EXT */
        /* Timestamp */

        /* UNKNOWN */
        | _ => (ReasonReact.null, rest)
        }
      };
    };
    let rec parseHexUntilDone = (~res=[], hex) =>
      switch (hex) {
      | [] => res
      | _ =>
        let (el, rest) = parseHex(hex);
        parseHexUntilDone(~res=[el, ...res], rest);
      };
    let cells = parseHexUntilDone(data)->List.rev->Array.of_list;
    <div style={ReactDOMRe.Style.make(~display="flex", ())}>
      {ReasonReact.array(cells)}
    </div>;
  },
};