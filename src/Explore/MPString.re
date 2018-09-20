let component = ReasonReact.statelessComponent("MPString");

let make = (~header, ~data, _children) => {
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
      <Block
        header={Printf.sprintf("str(%i)", Array.length(data))}
        raw=header
      />
      {
        ReasonReact.array(
          Array.map(
            c => <Block raw=c header={String.make(1, c->char_of_int)} />,
            data,
          ),
        )
      }
    </div>,
};