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
              if (i mod 2 == 0) {
                ReasonReact.null;
              } else {
                let lastEl = mapContent[i - 1];
                ReasonReact.array([|
                  <div style={ReactDOMRe.Style.make(~width="100%", ())} />,
                  <div
                    style={
                      ReactDOMRe.Style.make(
                        ~display="flex",
                        ~alignItems="center",
                        ~margin="4px",
                        (),
                      )
                    }>
                    lastEl
                    el
                  </div>,
                |]);
              },
            mapContent,
          ),
        )
      }
    </div>,
};