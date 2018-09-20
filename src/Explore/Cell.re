let component = ReasonReact.statelessComponent("Cell");

let make = (~data, _children) => {
  ...component,
  render: _self => {
    let rec parseHex = (~res=[], hex) => {
      let key = List.length(hex)->string_of_int;
      switch (hex) {
      | [] => res
      | [a, ...rest] =>
        switch (a) {
        /* NIL */
        | 0xc0 =>
          parseHex(~res=[<Block header="Nil" raw=[a] key />, ...res], rest)

        /* BOOLEANS */
        | 0xc2 =>
          parseHex(
            ~res=[<Block header="false" raw=[a] key />, ...res],
            rest,
          )

        | 0xc3 =>
          parseHex(~res=[<Block header="true" raw=[a] key />, ...res], rest)

        /* INTEGERS */
        | _ when a < 0b10000000 =>
          /* positive 7 bit int */
          let num =
            try (Printf.sprintf("0x%02X", a)->int_of_string) {
            | _ => 0
            };
          parseHex(
            ~res=[<Block header=num->string_of_int raw=[a] key />, ...res],
            rest,
          );

        | _ when a >= 0b11100000 =>
          /* negative 5 bit int */
          let num =
            (
              try (Printf.sprintf("0x%02X", a)->int_of_string) {
              | _ => 0
              }
            )
            - 256;
          parseHex(
            ~res=[<Block header=num->string_of_int raw=[a] key />, ...res],
            rest,
          );

        | 0xcc =>
          /* uint 8 */
          let head = List.hd(rest);
          let tail = List.tl(rest);
          let num = head->string_of_int;

          parseHex(
            ~res=[
              <MPInt header="uint 8" headerRaw=a raw=[head] num key />,
              ...res,
            ],
            tail,
          );

        | 0xcd =>
          /* uint 16 */
          let (raw, tail) = Util.splitAt(rest, 2);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
              )
              ->int_of_string
              ->string_of_int
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="uint 16" headerRaw=a raw num key />, ...res],
            tail,
          );

        | 0xce =>
          /* uint 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
              )
              ->int_of_string
              ->string_of_int
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="uint 32" headerRaw=a raw num key />, ...res],
            tail,
          );

        | 0xcf =>
          /* uint 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
                List.nth(raw, 4),
                List.nth(raw, 5),
                List.nth(raw, 6),
                List.nth(raw, 7),
              )
              ->Int64.of_string
              ->Int64.to_string
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="uint 64" headerRaw=a raw num key />, ...res],
            tail,
          );

        | 0xd0 =>
          /* int 8 */
          let head = List.hd(rest);
          let tail = List.tl(rest);
          let num = head->Int64.of_int->Util.addSign(8);

          parseHex(
            ~res=[
              <MPInt header="uint 8" headerRaw=a raw=[head] num key />,
              ...res,
            ],
            tail,
          );

        | 0xd1 =>
          /* uint 16 */
          let (raw, tail) = Util.splitAt(rest, 2);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
              )
              ->Int64.of_string
              ->Util.addSign(16)
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="int 16" headerRaw=a raw num key />, ...res],
            tail,
          );

        | 0xd2 =>
          /* int 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          Js.log(
            Printf.sprintf(
              "0x%02X%02X%02X%02X",
              List.nth(raw, 0),
              List.nth(raw, 1),
              List.nth(raw, 2),
              List.nth(raw, 3),
            ),
          );
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
              )
              ->Int64.of_string
              ->Util.addSign(32)
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="int 32" headerRaw=a raw num key />, ...res],
            tail,
          );

        | 0xd3 =>
          /* uint 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
                List.nth(raw, 4),
                List.nth(raw, 5),
                List.nth(raw, 6),
                List.nth(raw, 7),
              )
              ->Int64.of_string
              ->Util.addSign(64)
            ) {
            | _ => "?"
            };

          parseHex(
            ~res=[<MPInt header="int 64" headerRaw=a raw num key />, ...res],
            tail,
          );

        /* FLOATS (doesn't work) */
        | 0xca =>
          /* Float 32 */
          let (raw, tail) = Util.splitAt(rest, 4);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
              )
              ->float_of_string
            ) {
            | _ => nan
            };
          parseHex(~res=[<MPFloat header=a raw num key />, ...res], tail);

        | 0xcb =>
          /* Float 64 */
          let (raw, tail) = Util.splitAt(rest, 8);
          let num =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X%02X%02X%02X%02X",
                List.nth(raw, 0),
                List.nth(raw, 1),
                List.nth(raw, 2),
                List.nth(raw, 3),
                List.nth(raw, 4),
                List.nth(raw, 5),
                List.nth(raw, 6),
                List.nth(raw, 7),
              )
              ->float_of_string
            ) {
            | _ => nan
            };
          parseHex(~res=[<MPFloat header=a raw num key />, ...res], tail);

        /* STRINGS */
        | _ when a >= 0xA0 && a <= 0xBF =>
          /* 1 Byte String Header */
          let mask = 0b00011111->Int32.of_int;
          let len = Int32.of_int(a)->Int32.logand(mask)->Int32.to_int;
          let (strContent, tail) = Util.splitAt(rest, len);
          parseHex(
            ~res=[<MPString header=[a] len strContent key />, ...res],
            tail,
          );

        | 0xd9 =>
          /* 2 Byte String Header */
          let head = List.hd(rest);
          let len = head;
          let (strContent, tail) = Util.splitAt(List.tl(rest), len);
          parseHex(
            ~res=[<MPString header=[a, head] len strContent key />, ...res],
            tail,
          );

        | 0xda =>
          /* 2 Byte String Header */
          let (head, rest) = Util.splitAt(rest, 2);
          let len =
            try (
              Printf.sprintf(
                "0x%02X%02X",
                List.nth(head, 0),
                List.nth(head, 1),
              )
              ->int_of_string
            ) {
            | _ => 0
            };
          let (strContent, tail) = Util.splitAt(rest, len);
          parseHex(
            ~res=[
              <MPString header=[a, ...head] len strContent key />,
              ...res,
            ],
            tail,
          );

        | 0xdb =>
          /* 4 Byte String Header */
          let (head, rest) = Util.splitAt(rest, 4);
          let len =
            try (
              Printf.sprintf(
                "0x%02X%02X%02X%02X",
                List.nth(head, 0),
                List.nth(head, 1),
                List.nth(head, 2),
                List.nth(head, 3),
              )
              ->int_of_string
            ) {
            | _ => 0
            };
          let (strContent, tail) = Util.splitAt(rest, len);
          parseHex(
            ~res=[
              <MPString header=[a, ...head] len strContent key />,
              ...res,
            ],
            tail,
          );

        /* Binary */
        | 0xc4 =>
          /* 1 Byte Binary Header */
          res

        | 0xc5 =>
          /* 2 Byte Binary Header */
          res

        | 0xc6 =>
          /* 2 Byte Binary Header */
          res

        /* Array */
        | 0xAA =>
          /* Included Array Header */
          res

        | 0xdc =>
          /* 2 Byte Array Header */
          res

        | 0xdd =>
          /* 4 Byte Array Header */
          res

        /* Map */
        | 0xAB =>
          /* Included Map Header */
          res

        | 0xde =>
          /* 2 Byte Map Header */
          res

        | 0xdf =>
          /* 4 Byte Map Header */
          res

        /* Unimplemented */
        /* Maybe throw error and use componentDidCatch to display msg */
        /* EXT */
        /* Timestamp */

        /* UNKNOWN */
        | _ => res
        }
      };
    };
    let cells = parseHex(data)->List.rev->Array.of_list;
    <div style={ReactDOMRe.Style.make(~display="flex", ())}>
      {ReasonReact.array(cells)}
    </div>;
  },
};