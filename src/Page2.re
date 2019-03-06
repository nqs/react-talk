let component = ReasonReact.statelessComponent("Page2");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Page2">
      <h1> ("Page2" |> ReasonReact.string) </h1>
    </div>
};