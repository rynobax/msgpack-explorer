let component = ReasonReact.statelessComponent("MPArray");

let make =
    (
      ~header: list(int),
      ~arrContent: array(ReasonReact.reactElement),
      ~len: int,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~display="flex",
          ~border="1px solid black",
          (),
        )
      }>
      <Block header={Printf.sprintf("arr(%i)", len)} raw=header />
      {ReasonReact.array(arrContent)}
    </div>,
};