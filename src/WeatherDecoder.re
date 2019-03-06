type weather = {
  temperature: float,
  description: string,
}
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