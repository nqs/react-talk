let component = ReasonReact.statelessComponent("Page1");

let make = _children => {
  ...component,
  render: _self =>
    <div className="page1">
      <h1>("Page 1 Content" |> ReasonReact.string)</h1>
    </div>,
};