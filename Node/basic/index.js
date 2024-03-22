import { pid } from "node:process";
import childProcess from "child_process";
import os from "os";

const cpus = os.cpus();
// console.log(JSON.stringify(cpus, null, 4));
const cpuNum = cpus.length;
const workerTable = [];
for (let i = 0; i < cpuNum; ++i) {
  let worker = childProcess.fork("./worker.js");
  workerTable.push(worker);
}
workerTable.forEach((w, i) => {
  w.send(`hello from master, worker--${i}`);
  w.on("message", (msg) => {
    console.log(`Received message from worker--${i}:` + msg);
  });
});
console.log(`Master pid ${pid}`);
