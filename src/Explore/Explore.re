let component = ReasonReact.statelessComponent("Explore");

let make = (~dataString, _children) => {
  ...component,
  render: _self => {
    let hexList =
      Array.map(s => "0x" ++ s, Js.String.split(" ", dataString));
    let intOfStringSafe = str =>
      try (int_of_string(str)) {
      | _ => 0
      };
    let capitalHexList = Array.map(intOfStringSafe, hexList)->Array.to_list;
    <div style={ReactDOMRe.Style.make(~width="100%", ~height="100%", ())}>
      <Cell data=capitalHexList />
    </div>;
  },
};