let component = ReasonReact.statelessComponent("Explore");

let make = (~dataString, _children) => {
  ...component,
  render: _self => {
    let hexList =
      Array.map(s => "0x" ++ s, Js.String.split(" ", dataString));
    let capitalHexList = Array.map(int_of_string, hexList)->Array.to_list;
    <div style={ReactDOMRe.Style.make(~width="100%", ~height="100%", ())}>
      <Cell data=capitalHexList />
    </div>;
  },
};