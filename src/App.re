type state = {dataString: string};

type action =
  | DataChange(string);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    dataString: "de 00 12 a1 30 00 a1 31 01 a1 32 02 a1 33 03 a1 34 04 a1 35 05 a1 36 06 a1 37 07 a1 38 08 a1 39 09 a2 31 30 0a a2 31 31 0b a2 31 32 0c a2 31 33 0d a2 31 34 0e a2 31 35 0f a2 31 36 10 a2 31 37 11",
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