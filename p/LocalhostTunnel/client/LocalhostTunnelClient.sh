#!/bin/bash
(cd "$( dirname "${BASH_SOURCE[0]}" )";cd build; run-external-cmd sh -c './LocalhostTunnelClient 28422 1>>LocalhostTunnelClientOut 2>>LocalhostTunnelClientErr')
