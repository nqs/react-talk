type weather = {
  temperature: float,
  description: string,
};

type state =
  | Loading
  | Error
  | Loaded(weather);

type action =
  | WeatherFetch
  | WeatherFetched(weather)
  | WeatherFailedToFetch;

type weatherProperties = {
  periods: list(weather),
}
type weatherResponse = {
  properties: weatherProperties,
}
let decodeWeatherPeriod= json =>
  Json.Decode.{
    temperature: json |> field("temperature", float),
    description: json |> field("detailedForecast", string),
  };
let decodeWeatherProperties= json =>
  Json.Decode.{
    periods: json |> field("periods", list(decodeWeatherPeriod)),
  };
let decodeWeatherResponse= json =>
  Json.Decode.{
    properties: json |> field("properties", decodeWeatherProperties),
  };
let component = ReasonReact.reducerComponent("Home");

let make =  _children => {
  ...component,
  initialState: _state => Loading,
  didMount: self => self.send(WeatherFetch),
  reducer: (action, _state) =>
    switch (action) {
    | WeatherFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Axios.get("https://api.weather.gov/gridpoints/PBZ/77,65/forecast")
              |> then_(response => 
                response##data |> decodeWeatherResponse
                |> weatherResponse => weatherResponse.properties.periods 
                  |> List.hd
                |> weather => self.send(WeatherFetched(weather))
                |> resolve
              )
              |> catch((error) =>{ Js.log(error); resolve(self.send(WeatherFailedToFetch));})
              |> ignore
            )
        ),
      )
    | WeatherFetched(weather) => ReasonReact.Update(Loaded(weather))
    | WeatherFailedToFetch=> ReasonReact.Update(Error)
  },
  render: self =>
    switch (self.state) {
      | Error=> 
        <div>
          <h1>(ReasonReact.string("Error!"))</h1>
        </div>
      | Loading => <div> (ReasonReact.string("Loading...")) </div>
      | Loaded(weather) =>
        <div>
          <h1>(ReasonReact.string("Weather")) </h1>
          <div>
            <label>(ReasonReact.string("Temperature"))</label>
            <div>(ReasonReact.string(string_of_float(weather.temperature)))</div>
          </div>
          <div>
            <label>(ReasonReact.string("Description"))</label>
            <div>(ReasonReact.string(weather.description))</div>
          </div>
        </div>
  },
};