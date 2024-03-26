(function () {
  "use strict";
  var rates = ["1.0", "1.5", "2.0", "2.5", "3.0", "4.0"];
  document.addEventListener("readystatechange", function () {
      var stylesheet = document.createElement("style");
      stylesheet.setAttribute("type", "text/css");
      stylesheet.setAttribute("id", "cw__video_rate_plugin_style");
      stylesheet.innerText =
          "#cw__video_rate_plugin_box{opacity:.7;position:fixed;bottom:10px;left:10px;z-index:99999;display:flex;flex-direction:row;min-width:100px;padding:10px;border-radius: 6px;background-color: rgb(241 245 249);box-shadow: 0 25px 50px -12px rgb(30 58 138 / 0.25);}" +
          " .cw__video_rate_plugin_button{cursor: pointer;width:50px;height:30px;margin-right:10px;text-align:center;border-radius: 6px;line-height:30px;box-shadow: 0 10px 15px -3px rgb(29 78 216 / 0.5), 0 4px 6px -4px rgb(29 78 216 / 0.5);}" +
          " .cw__video_rate_plugin_button.text{width:90px;font-size:0.8rem;}" +
          " .cw__video_rate_plugin_button:active{opacity:.5;}" +
          " .cw__video_rate_plugin_button.text:active{opacity:1;}";
      var body = document.getElementsByTagName("body")[0];
      console.log(body);
      if (!document.getElementById("#cw__video_rate_plugin_style")) {
          body.append(stylesheet);
      }
      var videoEls = document.getElementsByTagName("video");
      // if (videoEls.length <= 0) return;
      if (!document.getElementById("#cw__video_rate_plugin_box")) {
          var frameEl = document.createDocumentFragment();
          var box = document.createElement("div");
          frameEl.appendChild(box);
          box.setAttribute("id", "cw__video_rate_plugin_box");
          var curRateEl = document.createElement("div");
          curRateEl.className += "cw__video_rate_plugin_button text";
          curRateEl.innerHTML = "RATE: " + rates[0];
          for (let i = 0; i < rates.length; i++) {
              var btn = document.createElement("div");
              btn.innerHTML = rates[i];
              btn.className += "cw__video_rate_plugin_button";
              btn.addEventListener("click", function () {
                  let rate = rates[i];
                  for (let j = 0; j < videoEls.length; j++) {
                      const vEl = videoEls[j];
                      vEl.playbackRate = rate * 1;
                      curRateEl.innerHTML = "RATE: " + rate;
                  }
              });
              box.appendChild(btn);
          }
          box.appendChild(curRateEl);
          body.append(box);
      }
  });
})();
