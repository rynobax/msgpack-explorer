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
      <Cell header={Printf.sprintf("map(%i)", len / 2)} raw=header />
      {
        ReasonReact.array(
          Array.mapi(
            (i, el) =>
              i mod 2 == 0 ?
                ReasonReact.array([|
                  <div style={ReactDOMRe.Style.make(~width="100%", ())} />,
                  el,
                |]) :
                ReasonReact.array([|
                  <div style={ReactDOMRe.Style.make(~width="24px", ())} />,
                  el,
                |]),
            mapContent,
          ),
        )
      }
    </div>,
};