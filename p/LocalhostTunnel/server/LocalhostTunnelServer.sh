#!/bin/bash
(cd "$( dirname "${BASH_SOURCE[0]}" )";cd build; run-external-cmd sh -c './LocalhostTunnelServer 1>>LocalhostTunnelServerOut 2>>LocalhostTunnelServerErr')
