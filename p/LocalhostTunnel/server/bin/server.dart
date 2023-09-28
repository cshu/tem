//import 'dart:convert';
import 'dart:typed_data';
import 'dart:io';
//import 'dart:isolate';
import 'package:async/async.dart';
import 'package:collection/collection.dart';
import 'package:convert/convert.dart';
import 'package:path/path.dart' as path;
import 'package:typed_data/typed_data.dart';
import 'package:dartrs/dartrs.dart';
import 'package:dfrs/dfrs.dart';

const tcpPortLocalhostTunnelServer = 28426;

void main(List<String> arguments) async {
  Process guiProc;
  if (Platform.isLinux) {
    guiProc = await Process.start('run-external-cmd', [
      '-wait-stdin',
      'xmessage',
      'LocalhostTunnelServer. To exit, click okay.'
    ]);
    guiProc.exitCode.then((int pr) {
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

  String adir = getHomeDir()!;
  adir = path.join(adir, '.everycom');
  var localOnly = path.join(adir, 'local_only');
  var notLocalOnly = path.join(adir, 'not_local_only');
  var defaultPemPassPhrasePath =
      path.join(notLocalOnly, 'default_pem_pass_phrase');
  var defaultPemPassPhrase = getFirstLineFromFile(defaultPemPassPhrasePath);
  var defaultLocalKeyPath = path.join(localOnly, 'default_local_key.pem');
  var defaultTokenPath = path.join(notLocalOnly, 'default_token');
  List<int> defaultToken = hex.decode(getFirstLineFromFile(defaultTokenPath));

  print('Hello world!');
  var debug1 = 1; //remove
  SecurityContext serverSecurityContext = SecurityContext()
    ..useCertificateChain(path.join(localOnly, 'default_cert.pem'))
    ..usePrivateKey(defaultLocalKeyPath, password: defaultPemPassPhrase);
  SecureServerSocket.bind(InternetAddress.anyIPv4, tcpPortLocalhostTunnelServer,
          serverSecurityContext)
      .then((secureServerSocket) {
    secureServerSocket.listen((secureSocket) async {
      Function eq = const ListEquality().equals;
      var debug2 = debug1;
      ++debug1;
      //List<int> temSocketOut;
      var temSocketOut = Uint8Buffer();
      var temNextSockeOut = Uint8Buffer();
      //int portNum;
      var events = StreamQueue<Uint8List>(secureSocket);
      //todo add timeout for defaultToken checking
      Uint8List temView = await fetchBytesIntoBuffer(
          events, defaultToken.length, temSocketOut, temNextSockeOut);
      bool tokenValid = eq(defaultToken, temView);
      if (!tokenValid) {
        //throw CommonException('Invalid Token');
        print('Token is INVALID!!!!!!!!!');
        //todo log remote ip, etc.
        events.cancel();
        secureSocket.destroy();
        return;
      }
      temSocketOut = temNextSockeOut;
      temNextSockeOut = Uint8Buffer();
      temView =
          await fetchBytesIntoBuffer(events, 2, temSocketOut, temNextSockeOut);
      int portNum = temSocketOut.buffer.asByteData().getUint16(0);
      //for(;;){
      //	var first = await events.next;
      //	temSocketOut.addAll(first);
      //	if(temSocketOut.length>=2){
      //		portNum = temSocketOut.buffer.asByteData().getUint16(0);
      //		temSocketOut = Uint8Buffer()..addAll(temSocketOut.sublist(2));
      //		break;
      //	}
      //}
      temSocketOut = temNextSockeOut;
      print('port num:' + portNum.toString());
      Socket sock = await Socket.connect(InternetAddress.loopbackIPv4, portNum);
      sock.listen((Uint8List dataEvent) {
        print('print debug2:' + debug2.toString());
        secureSocket.add(dataEvent);
      });
      sock.add(temSocketOut);
      for (;;) {
        print('print debug2:' + debug2.toString());
        //print(utf8.decoder.convert(temSocketOut));
        //temSocketOut = Uint8Buffer()..addAll(await events.next);
        if (!(await events.hasNext)) {
          sock.destroy();
          events.cancel();
          secureSocket.destroy();
          print('all destroyed!!! ' + debug2.toString());
          break;
        }
        sock.add(await events.next);
      }
    });
  });
}

//todo use a list to store all active connections, so when you close the server app, destroy all the active connections properly? (But maybe it's not that important? Just let it be?)
