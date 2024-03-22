import process from "node:process";
console.log(`Worker pid ${process.pid}`);
// 接收主进程发来的消息
process.on("message", (msg) => {
  console.log("Received message:" + msg);
  // 子进程向主进程发送消息
  process.send(`Hi master. my pid is ${process.pid} ppid is ${process.ppid}`);
});
