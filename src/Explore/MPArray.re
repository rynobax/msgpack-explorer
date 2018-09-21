let component = ReasonReact.statelessComponent("MPArray");

let make =
    (~header: list(int), ~arrContent: list(int), ~len: int, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~backgroundColor="#EFE",
          ~display="flex",
          (),
        )
      }>
      <Block header={Printf.sprintf("arr(%i)", len)} raw=header />
      {
        ReasonReact.array(
          Array.mapi(
            (i, c) =>
              <Block
                raw=[c]
                header={String.make(1, c->char_of_int)}
                key={string_of_int(i)}
              />,
            arrContent->Array.of_list,
          ),
        )
      }
    </div>,
};