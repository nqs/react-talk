let component = ReasonReact.statelessComponent("App");

let make = (~currentRoute: Router.route, _children) => {
  ...component,
  render: self =>
    <div>
      <header>
        <h1> (currentRoute.title |> ReasonReact.string) </h1>
      </header>
      <header>
        <nav>
          <label> ("Home Title" |> ReasonReact.string) </label>
          <ul>
            <li>
              <Router.NavLink href="/">
                ("Home" |> ReasonReact.string)
              </Router.NavLink>
            </li>
          </ul>
          <label> ("pages" |> ReasonReact.string) </label>
          <ul>
            <li>
              <Router.NavLink href="/page1">
                ("Page1" |> ReasonReact.string)
              </Router.NavLink>
            </li>
            <li>
              <Router.NavLink href="/page2">
                ("Page2" |> ReasonReact.string)
              </Router.NavLink>
            </li>
            <li>
              <Router.NavLink href="/page3">
                ("Page3" |> ReasonReact.string)
              </Router.NavLink>
            </li>
          </ul>
        </nav>
      </header>
      <main>
        currentRoute.component
      </main>
    </div>,
};
