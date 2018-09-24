let component = ReasonReact.statelessComponent("MPString");

let make =
    (~header: list(int), ~strContent: list(int), ~len: int, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~backgroundColor=Color.string,
          ~display="flex",
          (),
        )
      }>
      <Cell header={Printf.sprintf("str(%i)", len)} raw=header />
      <Cell
        raw=strContent
        header={
          String.concat(
            "",
            List.map(c => String.make(1, c->char_of_int), strContent),
          )
        }
      />
    </div>,
};