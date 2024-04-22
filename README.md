## Full reproduction steps:

```bash
git clone https://github.com/gmcchessney/gRPC-UDS-RST_STREAM-Error.git
cd gRPC-UDS-RST_STREAM-Error

cmake -S ./CppClient -B ./CppClient/out
cmake --build ./CppClient/out

dotnet build ./CSharpServer

# Run the csharp server
./CSharpServer/bin/Debug/net8.0/CSharpServer

# In a separate terminal, run the cpp client
./CppClient/out/CppClient
```
