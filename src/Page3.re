let component = ReasonReact.statelessComponent("Page3");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Page3">
      <h1> ("Page 3 Content" |> ReasonReact.string) </h1>
    </div>
};