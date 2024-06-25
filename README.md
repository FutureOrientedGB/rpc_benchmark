| **rpc framework**     | **content size**             | **batch size** | **times** | **avg elapsed seconds** |
|-----------------------|------------------------------|----------------|-----------|-------------------------|
| **Apache Thrift C++** | 48 (unary)                   | 100,000        | 20        |  4.93                   |
| **Google gRPC C++**   | 48 (unary)                   | 100,000        | 20        |  15.47                  |
| **WellTrans rimi**    | 48 (unary)                   | 100,000        | 20        |  15.47                  |
| **WellTrans rsio**    | 48 (unary)                   | 100,000        | 20        |  15.47                  |
|                       |                              |                |           |                         |
| **Apache Thrift C++** | 1400 (callback)              | 100,000        | 20        |  12.29                  |
| **Google gRPC C++**   | 1400 (bidirectional stream)  | 100,000        | 20        |  10.45                  |
| **WellTrans rimi**    | 1400 (bidirectional stream)  | 100,000        | 20        |  10.45                  |
| **WellTrans rsio**    | 1400 (bidirectional stream)  | 100,000        | 20        |  10.45                  |
