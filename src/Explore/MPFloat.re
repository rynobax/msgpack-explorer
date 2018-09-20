let component = ReasonReact.statelessComponent("MPString");

let make = (~header: int, ~raw: list(int), ~num: float, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~backgroundColor="#EEF",
          ~display="flex",
          (),
        )
      }>
      <Block header="float 32" raw=[header] />
      <Block header={Printf.sprintf("%f", num)} raw />
    </div>,
};