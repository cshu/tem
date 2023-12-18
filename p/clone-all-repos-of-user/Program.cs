using System.Text.Json;


//var usernm = Environment.GetCommandLineArgs()[1];
var usernm = args[0];
var url = "https://api.github.com/users/" + usernm + "/repos";
var pagecount = 1;
var lastpage = 0;
var repos = new List<Repo>();
Console.WriteLine("GET " + url);
using HttpClient client = new();
client.DefaultRequestHeaders.Add("User-Agent", "curl/7.81.0");
for (; ; ++pagecount)
{
    using HttpResponseMessage hrm = await client.GetAsync(pagecount == 1 ? url : url + "?page=" + pagecount);
    await using Stream stream = await hrm.Content.ReadAsStreamAsync();
    List<Repo> repoarr = (await JsonSerializer.DeserializeAsync<List<Repo>>(stream))!;
    Console.WriteLine($"{repoarr.Count} repos in response");
    repos.AddRange(repoarr);
    if (lastpage == 0)
    {
        IEnumerable<string>? linkhdr;
        if (hrm.Headers.TryGetValues("Link", out linkhdr))
        {
            var linkval = linkhdr.Last();
            var pattern = "/repos?page=";
            var pageeq = linkval.LastIndexOf(pattern);
            if (pageeq != -1 && linkval.EndsWith("rel=\"last\""))
            {
                var pagebeg = pageeq + pattern.Length;
                var pageend = linkval.IndexOf(">", pagebeg);
                if (pageend != -1)
                {
                    lastpage = int.Parse(linkval.Substring(pagebeg, pageend - pagebeg));
                    Console.WriteLine($"Found total number of pages: {lastpage}");
                    if (lastpage > 1) continue;
                }
            }
        }
        break;
    }
    else
    {
        if (pagecount == lastpage) break;
    }
}
//await using Stream stream = await client.GetStreamAsync(url);
//List<Repo> repos = (await JsonSerializer.DeserializeAsync<List<Repo>>(stream))!;
int forkcount = 0;
int existcount = 0;
int clonecount = 0;
foreach (var repo in repos)
{
    var rnm = repo.Name;
    if (repo.Fork)
    {
        ++forkcount;
        Console.WriteLine($"Skipping {rnm} because it is a fork");
        continue;
    }
    if (Path.Exists(rnm))
    {
        ++existcount;
        Console.WriteLine($"Skipping {rnm} due to filesystem entry conflict");
        continue;
    }
    ++clonecount;
    var proc = System.Diagnostics.Process.Start("git", "clone https://" + usernm + "@github.com/" + usernm + "/" + rnm);
    proc.WaitForExit();
}
Console.WriteLine($"FORK {forkcount}\nCONFLICT {existcount}\nCLONE {clonecount}\nTOTAL {repos.Count}");
