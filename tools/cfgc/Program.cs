using System;
using System.IO;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace Cs2Opt.Cfgc;

// Small C# helper that rewrites config/optimizer.json when the user
// runs `cfg set <key> <value>` from the CLI. Kept separate from the
// native binary so config editing never touches the game process.
internal static class Program
{
    private static int Main(string[] args)
    {
        if (args.Length < 3 || args[0] != "set")
        {
            Console.Error.WriteLine("usage: cfgc set <key> <value>");
            return 1;
        }

        var path = Path.Combine(AppContext.BaseDirectory, "config", "optimizer.json");
        if (!File.Exists(path))
        {
            Console.Error.WriteLine($"missing {path}");
            return 2;
        }

        var node = JsonNode.Parse(File.ReadAllText(path))!.AsObject();
        var key = args[1];
        if (!node.ContainsKey(key))
        {
            Console.Error.WriteLine($"unknown key: {key}");
            return 3;
        }

        node[key] = ParseValue(args[2]);
        var opts = new JsonSerializerOptions { WriteIndented = true };
        File.WriteAllText(path, node.ToJsonString(opts));
        Console.WriteLine($"set {key} = {args[2]}");
        return 0;
    }

    private static JsonNode ParseValue(string raw)
    {
        if (bool.TryParse(raw, out var b)) return JsonValue.Create(b)!;
        if (int.TryParse(raw, out var i))  return JsonValue.Create(i)!;
        return JsonValue.Create(raw)!;
    }
}