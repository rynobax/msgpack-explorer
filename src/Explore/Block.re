let component = ReasonReact.statelessComponent("MPString");

let make = (~header, ~raw, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="2px",
          ~display="flex",
          ~flexDirection="column",
          ~justifyContent="center",
          ~textAlign="center",
          (),
        )
      }>
      <div> {ReasonReact.string(header)} </div>
      <div> {ReasonReact.string(Printf.sprintf("%X", raw))} </div>
    </div>,
};