using CSharpServer.Services;
using Microsoft.AspNetCore.Server.Kestrel.Core;

namespace CSharpServer
{
    public class Program
    {
        private const string IPC_PATH = "/run/my_app.sock";

        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            builder.WebHost.ConfigureKestrel(serverOptions =>
            {
                serverOptions.ListenUnixSocket(IPC_PATH, listenOptions =>
                {
                    listenOptions.Protocols = HttpProtocols.Http2;
                });
            });

            // Add services to the container.
            builder.Services.AddGrpc();

            var app = builder.Build();

            // Configure the HTTP request pipeline.
            app.MapGrpcService<GreeterService>();

            app.Run();
        }
    }
}