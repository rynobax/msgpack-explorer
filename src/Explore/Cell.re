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
        | 0xc0 =>
          parseHex(~res=[<Block header="Nil" raw=[a] key />, ...res], rest)
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
              Printf.sprintf("0x%X%X", List.nth(head, 0), List.nth(head, 1))
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
                "0x%X%X%X%X",
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