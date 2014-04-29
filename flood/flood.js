(function() {
    var intervalId;

    window.onload = function() {
        // Set Canvas
        var c = document.getElementById("flood");
        c.width = 640;
        c.height = 480;
        c.style.border = "2px solid #333333";

        // Center buttons
        // var buttonContainer = document.getElementById("buttonContainer");
        // buttonContainer.style.textAlign = "center";

        var start = document.getElementById("start");
        start.onclick = run;
    };

    function run() {
        // Setup our rendering context
        var c = document.getElementById("flood");
        var ctx = c.getContext("2d");
        clearCanvas();

        var img = ctx.createImageData(c.width, c.height);

        var stack = [[Math.floor(Math.random()*(c.width-1)),
                      Math.floor(Math.random()*(c.height-1))]];

        var startColor = Math.random()*2*Math.PI;
        var FPS = 1000 / 60;
        var NUM_STEPS = 500;

        clearInterval(intervalId);
        intervalId = setInterval(function() {
            var steps = 0;
            while (steps < NUM_STEPS) {
                // Select the last pixel on the stack
                p = stack[stack.length-1];

                // Get all surrounding pixels
                adj = adjPixels(img, p[0], p[1], c.width, c.height)

                // check if we're surrounded, in which case we'll remove the last pixel.
                if (adj.length == 0) {
                    stack.pop()
                    if (stack.length == 0)
                        break;
                } else {
                    // Randomly select an adjacent pixel...
                    var pi = Math.floor(Math.random()*(adj.length));
                    var pn = adj[pi];

                    // and color it
                    rgb = hsvToRgb(((startColor+stack.length/(c.width*c.height))*2*Math.PI)%(2*Math.PI), 1, 1);
                    setPixel(img, pn[0], pn[1], rgb[0], rgb[1], rgb[2], 255);

                    // rgb = $.husl.toRGB(((startColor+stack.length/(c.width*c.height))*360)%(360), 70, 70);
                    // setPixel(img, pn[0], pn[1], rgb[0] * 255, rgb[1] * 255, rgb[2] * 255, 255);

                    stack.push(pn);
                    ++steps;
                }
            }

            ctx.putImageData(img, 0, 0);

            if (stack.length == 0) {
                clearInterval(intervalId);
            }
        }, FPS);
    }

    function clearCanvas() {
        var c = document.getElementById("flood");
        var ctx = c.getContext("2d");

        ctx.clearRect(0, 0, c.width, c.height);
    }

    // Returns a list of adjacent pixels
    function adjPixels(myimg, x, y, w, h) {
        var cs = [[x-1,y], [x+1,y], [x,y-1], [x,y+1]];
        var ps = [];
        for (var pi = 0; pi < cs.length; ++pi)
        {
            var xf = (w + cs[pi][0]) % w;
            var yf = (h + cs[pi][1]) % h;
            var i = (xf + yf * myimg.width) * 4;
            var add;
            add = (myimg.data[i] == 0 && myimg.data[i+1] == 0 && myimg.data[i+2] == 0);
            if (add)
                ps.push([xf, yf]);
        }
        return ps;
    }

    // Colors a pixel internally
    function setPixel(myimg, x, y, r, g, b, a) {
        index = (x + y * myimg.width) * 4;
        myimg.data[index+0] = r;
        myimg.data[index+1] = g;
        myimg.data[index+2] = b;
        myimg.data[index+3] = a;
    }

    // Returns the rgb representation of an HSV color
    function hsvToRgb(h, s, v) {
        var r = 0, g = 0, b = 0;
        var chroma = s * v;
        var hdash = h / (Math.PI / 3);
        var x = chroma*(1 - Math.abs(hdash % 2 - 1));

        if (hdash < 1)
            r = chroma, g = x;
        else if (hdash < 2)
            r = x, g = chroma;
        else if (hdash < 3)
            g = chroma, b = x;
        else if (hdash < 4)
            g = x, b = chroma;
        else if (hdash < 5)
            r = x, b = chroma;
        else if (hdash < 6)
            r = chroma, b = x;

        m = v - chroma;
        r = (r + m) * 255;
        g = (g + m) * 255;
        b = (b + m) * 255;
        return [r, g, b];
    }
})();
