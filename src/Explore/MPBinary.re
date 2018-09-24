let component = ReasonReact.statelessComponent("MPBinary");

let make =
    (~header: list(int), ~binContent: list(int), ~len: int, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~backgroundColor=Color.binary,
          ~display="flex",
          (),
        )
      }>
      <Cell header={Printf.sprintf("bin(%i)", len)} raw=header />
      {
        ReasonReact.array(
          Array.mapi(
            (i, c) => <Cell raw=[c] header="." key={string_of_int(i)} />,
            binContent->Array.of_list,
          ),
        )
      }
    </div>,
};