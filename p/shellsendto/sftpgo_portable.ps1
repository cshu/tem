$ErrorActionPreference = 'Stop';

cd ~/u/vcs/bb/homestuff/sftpgo_host_key
echo $args[0]
$dirToServe = rvpa $args[0]
pwd | write-host
~\u\bin\sftpgo\sftpgo.exe portable -g '*' -c '*' -d "$dirToServe" -s 60331 -k "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC2c+VAn6ogBQXYOKfNCXPljXizZHIGicXIzz4gt1UkzX5fttRPRJrBep6l096IDMEI/iBodmEDFLEmDQZmpRJzNOqXIk8jGpP+XYMFweABoM+u5U0PQESFHqHBcy4kM1Qg0gPGLGCz7k5RbpX8fxca//a9lahkBU/TXAFUdjLTwbc2gWXW0y1s1wOp5EeMn1uBfD2HA/dsrof75vrc4me99i6peDJSnsSKWL51+LX8zunq2EEohsYnf5YHg+33aZrxffKCBK5enzPs/hTq2yK9ZdEhjyVhKLTNpHtOKfqNFvhklvMSGsMgchD3/KxqL8kJihJbCV3UR2+MUcSghdG9"
echo ALLDONE
