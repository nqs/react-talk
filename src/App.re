let component = ReasonReact.statelessComponent("App");

let make = (~currentRoute: Router.route, _children) => {
  ...component,
  render: self =>
    <div>
      <header>
        <h1> (ReasonReact.string(currentRoute.title)) </h1>
      </header>
      <nav>
        <header>
        </header>
        <label> (ReasonReact.string("home label")) </label>
        <ul>
          <li>
            <Router.NavLink href="/">
              (ReasonReact.string("Home"))
            </Router.NavLink>
          </li>
        </ul>
        <label> (ReasonReact.string("pages")) </label>
        <ul>
          <li>
            <Router.NavLink href="/page1">
              (ReasonReact.string("Page1"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink href="/page2">
              (ReasonReact.string("Page2"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink href="/page3">
              (ReasonReact.string("Page3"))
            </Router.NavLink>
          </li>
        </ul>
      </nav>
      <main>
        currentRoute.component
      </main>
    </div>,
};
