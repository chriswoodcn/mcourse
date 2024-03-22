import childProcess from "child_process";
import os from "node:os";
import net from "node:net";

// 获取cpu的数量
const cpuNum = os.cpus().length;

let workers = [];

for (let i = 0; i < cpuNum; ++i) {
  workers.push(childProcess.fork("./worker.js"));
  console.log("worker process-" + workers[i].pid);
}

// 创建TCP服务器
const tcpServer = net.createServer();

tcpServer.listen(8989, () => {
  console.log("Tcp Server: 127.0.0.8989");
  // 监听端口后将服务器句柄发送给worker进程
  for (let i = 0; i < cpuNum; ++i) {
    workers[i].send("tcpServer", tcpServer);
  }
  // 关闭master线程的端口监听
  tcpServer.close();
});

/*
 服务器收到请求后分发给工作进程去处理
*/
tcpServer.on('connection', (socket) => {
  workers[cur].send('socket', socket);
  cur = Number.parseInt((cur + 1) % cpuNum);
});

tcpServer.listen(8989, () => {
  console.log('Tcp Server: 127.0.0.8989');
  // 监听端口后将服务器句柄发送给worker进程
  for (let i = 0; i < cpuNum; ++i) {
    workers[i].send('tcpServer', tcpServer);
    // 监听工作进程退出事件
    workers[i].on('exit', ((i) => {
      return () => {
        console.log('worker-' + workers[i].pid + ' exited');
        workers[i] = childProcess.fork('./worker.js');
        console.log('Create worker-' + workers[i].pid);
        workers[i].send('tcpServer', tcpServer);
      }
    })(i));
  }
  // 不能关闭master线程的，否则的话，句柄将为空，无法正常传递。
  // tcpServer.close();
});
