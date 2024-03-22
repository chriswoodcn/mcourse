import net from "node:net";
const maxConnectCount = 100;

for (let i = 0; i < maxConnectCount; ++i) {~
  net
    .createConnection({
      port: 8989,
      host: "127.0.0.1",
    })
    .on("data", (d) => {
      console.log(d.toString());
    });
}
