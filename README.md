<!--
To compile puml use: (Assuming plantuml you are in the directory)
plantuml.jar -tsvg readme.md -o diagrams
-->


szs_time_sync

version = 0.2.1


## Dependencies
| Dependency version | Version number |
|---|---|
|DataTransport|0.3.0|


## Flow run

<!--
```
@startuml flow_run

start

:Set RTT filter;
:Reset time;
repeat
    :Sync with server;
    repeat while (Check that sync is ok) is (false)
:"Sync Successful";

stop

@enduml
```
-->

![](diagrams/flow_run.svg)
