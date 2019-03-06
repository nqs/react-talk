let component = ReasonReact.statelessComponent("App");

let make = (~currentRoute: Router.route, _children) => {
  ...component,
  render: self =>
    <div className="container-fluid">
          <ul className="nav nav-pills justify-content-center">
            <li className="nav-item">
              <Router.NavLink href="/">
                ("Home" |> ReasonReact.string)
              </Router.NavLink>
            </li>
            <li className="nav-item">
              <Router.NavLink href="/page1">
                ("Page1" |> ReasonReact.string)
              </Router.NavLink>
            </li>
            <li className="nav-item">
              <Router.NavLink href="/page2">
                ("Page2" |> ReasonReact.string)
              </Router.NavLink>
            </li>
            <li className="nav-item">
              <Router.NavLink href="/page3">
                ("Page3" |> ReasonReact.string)
              </Router.NavLink>
            </li>
          </ul>
      <main>
        currentRoute.component
      </main>
    </div>,
};
