let component = ReasonReact.statelessComponent("Cell");

let make = (~data, _children) => {
  ...component,
  render: _self => {
    let rec parseHex = (~res=[], hex) =>
      switch (hex) {
      | [] => res
      | [a, ...rest] =>
        switch (a) {
        | _ when a >= 0xA0 && a <= 0xBF =>
          /* String with len in hex */
          let len = 5;
          let (head, tail) = Util.splitAt(rest, len);
          parseHex(
            ~res=[<MPString data={Array.of_list(head)} />, ...res],
            tail,
          );
        | _ => res
        }
      };
    let cells = parseHex(data)->Array.of_list;
    <div> {ReasonReact.array(cells)} </div>;
  },
};