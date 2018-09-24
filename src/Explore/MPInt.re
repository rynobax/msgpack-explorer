let component = ReasonReact.statelessComponent("MPInt");

let make =
    (
      ~header: string,
      ~headerRaw: int,
      ~raw: list(int),
      ~num: string,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~backgroundColor=Color.int,
          ~display="flex",
          (),
        )
      }>
      <Block header raw=[headerRaw] />
      <Block header=num raw />
    </div>,
};