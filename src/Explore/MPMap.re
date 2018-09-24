let component = ReasonReact.statelessComponent("MPMap");

let make =
    (
      ~header: list(int),
      ~mapContent: array(ReasonReact.reactElement),
      ~len: int,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      className="MPMap"
      style={
        ReactDOMRe.Style.make(
          ~padding="5px",
          ~display="flex",
          ~flexWrap="wrap",
          ~border="1px solid black",
          ~backgroundColor=Color.map,
          (),
        )
      }>
      <Block header={Printf.sprintf("map(%i)", len / 2)} raw=header />
      {ReasonReact.array(mapContent)}
    </div>,
};