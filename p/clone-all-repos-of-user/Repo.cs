using System.Text.Json.Serialization;

public record class Repo(
    [property: JsonPropertyName("name")] string Name,
    [property: JsonPropertyName("fork")] bool Fork);
