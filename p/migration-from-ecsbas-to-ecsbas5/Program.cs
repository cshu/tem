using Microsoft.Data.Sqlite;


var ecsbas5dir = args[1];
var notedir = Path.Combine(ecsbas5dir, "note");
if (!Directory.Exists(notedir)) throw new Exception();
var migrated_from_ecsbas = Path.Combine(notedir, "migrated_from_ecsbas");
Directory.CreateDirectory(migrated_from_ecsbas);

var ecsbasdir = args[0];
if (!Directory.Exists(ecsbasdir)) throw new Exception();
var personal_use = Path.Combine(ecsbasdir, "personal_use");
if (!Directory.Exists(personal_use)) throw new Exception();
var notes = Path.Combine(ecsbasdir, "notes");
if (!Directory.Exists(notes)) throw new Exception();
Directory.SetCurrentDirectory(ecsbasdir);
using SqliteConnection con = new SqliteConnection("Data Source=_db/main");
con.Open();
Dictionary<long, string> singleArgVerb = new();
{
    using var command = con.CreateCommand();
    command.CommandText = @"select * from in_singleargv";
    using var rdr = command.ExecuteReader();
    while (rdr.Read())
    {
        var verb = rdr.GetInt64(0);
        var vdesc = rdr.GetString(1);
        singleArgVerb[verb] = '"' + vdesc + '"';
    }
}
//Dictionary<long, List<long>> singleArgPred = new();
Dictionary<long, List<string>> singleArgPred = new();
{
    using var command = con.CreateCommand();
    command.CommandText = @"select * from in_singleargp";
    using var rdr = command.ExecuteReader();
    while (rdr.Read())
    {
        var verb = rdr.GetInt64(0);
        var sid = rdr.GetInt64(1);
        if (verb < 297315)
        {
            Console.WriteLine($"IGNORING {verb}");
            continue;//297315 is min integer for normal id used by ECSBAS
        }
        string vdesc = singleArgVerb[verb];
        if (singleArgPred.ContainsKey(sid))
        {
            singleArgPred[sid].Add(vdesc);
        }
        else
        {
            var newList = new List<string>();
            newList.Add(vdesc);
            singleArgPred[sid] = newList;
        }
    }
}

List<(long, string, string)> textnotes = new();
{
    using var command = con.CreateCommand();
    command.CommandText = @"select * from sp_text_notes";
    using var rdr = command.ExecuteReader();
    while (rdr.Read())
    {
        var sid = rdr.GetInt64(0);
        var dirnm = rdr.GetString(1);
        var filenm = rdr.GetString(2);
        textnotes.Add((sid, dirnm, filenm));
    }
}
List<(long, string, string, string)> bms = new();
{
    using var command = con.CreateCommand();
    command.CommandText = @"select * from sp_urlbookmar";
    using var rdr = command.ExecuteReader();
    while (rdr.Read())
    {
        var sid = rdr.GetInt64(0);
        var url = rdr.GetString(1);
        var desc = rdr.GetString(2);
        var filenm = rdr.GetString(3);
        bms.Add((sid, url, desc, filenm));
    }
}
List<string> GetPred(long sid)
{
    List<string>? retval;
    if (singleArgPred.TryGetValue(sid, out retval)) return retval!;
    return new List<string>();
}
string MkInfo(long sid)
{
    return "{\"lbls\":[" + string.Join(",", GetPred(sid)) + "]}\n";
}
//foreach (var bm in bms)
foreach (var (bm, i) in bms.Select((bm, i) => (bm, i)))
{
    (var sid, var url, var desc, var filenm) = bm;
    var newnote = Path.Combine(migrated_from_ecsbas, "bm" + i);
    Directory.CreateDirectory(newnote);
    string info = MkInfo(sid);
    File.WriteAllText(Path.Combine(newnote, "info"), info);
    string note = url + "\n";
    if (desc.Length != 0) note += desc + "\n";
    File.WriteAllText(Path.Combine(newnote, "note"), note);
    if (filenm.Length != 0)
    {
        filenm += ".htm";
        string att = Path.Combine(newnote, "att");
        Directory.CreateDirectory(att);
        File.Copy(Path.Combine("_bookmark", filenm), Path.Combine(att, filenm));
    }
    //Console.WriteLine(newnote);
    //if (filenm.Length == 0) Console.WriteLine("EMPTY");
    //Console.WriteLine("FILENM"+filenm);
}
foreach (var tnote in textnotes)
{
    (var sid, var dirnm, var filenm) = tnote;
    var newnote = Path.Combine(migrated_from_ecsbas, filenm);
    Directory.CreateDirectory(newnote);
    string info = MkInfo(sid);
    File.WriteAllText(Path.Combine(newnote, "info"), info);
    File.Copy(Path.Combine(dirnm, filenm), Path.Combine(newnote, "note"));
}
