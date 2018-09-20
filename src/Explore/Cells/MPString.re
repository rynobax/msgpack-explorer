let component = ReasonReact.statelessComponent("MPString");

let make = (~data, _children) => {
  ...component,
  render: _self => {
    let strings = Array.map(e => Printf.sprintf("%c", e), data);
    <div
      style={
        ReactDOMRe.Style.make(~padding="5px", ~backgroundColor="#EFE", ())
      }>
      {ReasonReact.array(Array.map(ReasonReact.string, strings))}
    </div>;
  },
};