import 'dart:io';
import 'dart:typed_data';
import 'package:collection/collection.dart';
import 'package:convert/convert.dart';
import 'package:crypto/crypto.dart';
import 'package:path/path.dart' as path;
import 'package:dartrs/dartrs.dart';

const tcpPortLocalhostTunnelServer = 28426;
ServerSocket? defServerSocket;

void main(List<String> arguments) async {
  if (Platform.isLinux) {
    (await Process.start('run-external-cmd', [
      '-wait-stdin',
      'xmessage',
      'LocalhostTunnelClient. To exit, click okay.'
    ]))
        .exitCode
        .then((int pr) {
      exit(0);//note this program doesn't have finally or similar resource , so using exit is okay
    });
    //else if (Platform.isWindows) msg /w SessionId message
  } else {
    //throw CommonException('Platform not supported');
  }

  //?? this is not working?? the reason is addOnExitListener on current isolate cannot run when current isolate immediately dies?? So in the end you use 'run-external-cmd' '-wait-stdin' instead
  //Isolate.current.addOnExitListener(new RawReceivePort((event) {
  //  print('on exit: $event');
  //  guiProc?.kill();//? check returned bool is true?
  //}).sendPort);

  print(arguments[0]); //remove
  var portToListen = int.parse(arguments[0]);
  //todo try to get env var first (APP_DATA_EVERY_COM)
  String adir = getHomeDir()!;
  adir = path.join(adir, '.everycom');
  var localOnly = path.join(adir, 'local_only');
  var notLocalOnly = path.join(adir, 'not_local_only');
  var remoteInfo = path.join(localOnly, 'remote_info');
  var defaultRemotePath = path.join(remoteInfo, 'default_remote');
  var defaultRemote = getNonEmptyFirstLineFromFile(defaultRemotePath);
  var defaultCertSha256Path = path.join(localOnly, 'default_cert_sha256');
  var defaultCertSha256Str =
      getNonEmptyFirstLineFromFile(defaultCertSha256Path);
  var defaultCertSha256 = hex.decode(defaultCertSha256Str);
  var defaultTokenPath = path.join(notLocalOnly, 'default_token');
  var defaultToken = hex.decode(getFirstLineFromFile(defaultTokenPath));
  ServerSocket.bind(InternetAddress.loopbackIPv4, portToListen)
      .then((serverSocket) {
    defServerSocket = serverSocket;
    serverSocket.listen((socket) async {
      var secureSocket = await SecureSocket.connect(
          defaultRemote, tcpPortLocalhostTunnelServer,
          onBadCertificate: (certificate) {
        //print(sha256.convert(certificate.der).toString());
        Function eq = const ListEquality().equals;
        var retval =
            eq(sha256.convert(certificate.der).bytes, defaultCertSha256);
        //print(retval);
        return retval;
        //return true;
      });
      secureSocket.listen((Uint8List dataEvent) {
        socket.add(dataEvent);
      });
      secureSocket.add(defaultToken);
      secureSocket
          .add((ByteData(2)..setUint16(0, portToListen)).buffer.asUint8List());
      socket.listen((chunk) {
        secureSocket.add(chunk);
      }, onDone: () {
        print('debug browser conn listen ondone');
        socket.destroy();
        secureSocket.destroy();
      });
    });
  });
  //print('Use last server addr? ');
  //print('Or use a new one:');
}

//todo use a list to store all active connections, so when you close the server app, destroy all the active connections properly? (But maybe it's not that important? Just let it be?)
