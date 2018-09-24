type state = {dataString: string};

type action =
  | DataChange(string);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    dataString: "82 a7 63 6f 6d 70 61 63 74 c3 a6 73 63 68 65 6d 61 00",
  },
  reducer: (action, _state) =>
    switch (action) {
    | DataChange(str) => ReasonReact.Update({dataString: str})
    },
  render: self => {
    let dataString = String.trim(self.state.dataString);
    <div
      style={
        ReactDOMRe.Style.make(
          ~backgroundColor="#ededed",
          ~width="100vw",
          ~height="100vh",
          ~display="flex",
          (),
        )
      }>
      <div
        style={
          ReactDOMRe.Style.make(
            ~flex="0 0 300px",
            ~display="flex",
            ~flexDirection="column",
            (),
          )
        }>
        <Form
          value={self.state.dataString}
          onChange={str => self.ReasonReact.send(DataChange(str))}
        />
        <Result dataString />
      </div>
      <div style={ReactDOMRe.Style.make(~flex="1", ())}>
        <Explore dataString />
      </div>
    </div>;
  },
};