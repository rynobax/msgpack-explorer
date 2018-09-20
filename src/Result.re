let component = ReasonReact.statelessComponent("Result");

let make = _children => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~backgroundColor="papayawhip",
          ~width="100%",
          ~flex="1",
          (),
        )
      }>
      {ReasonReact.string("{ \"json\": \"here\" }")}
    </div>,
};