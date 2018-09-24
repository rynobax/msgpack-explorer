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
      <Block header={Printf.sprintf("str(%i)", len)} raw=header />
      {
        ReasonReact.array(
          Array.mapi(
            (i, c) =>
              <Block
                raw=[c]
                header={String.make(1, c->char_of_int)}
                key={string_of_int(i)}
              />,
            strContent->Array.of_list,
          ),
        )
      }
    </div>,
};