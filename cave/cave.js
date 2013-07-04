(function() {
    window.onload = function() {
        // Set Canvas
        var c = document.getElementById("cave");
        c.width = 640;
        c.height = 480;
        c.style.border = "2px solid #333333";

        var reset = document.getElementById("reset");
        reset.onclick = init;

        init();
    };

    function init() {
        var c = document.getElementById("cave");
        var cellSize = 8;
        var cellWidth = c.width / cellSize;
        var cellHeight = c.height / cellSize;
        var cells = buildArray(cellWidth, cellHeight);

        var color = Math.random()*2*Math.PI;

        clearCanvas();
        randomizeCells(cells, cellWidth, cellHeight);
        drawCells(cells, cellWidth, cellHeight, cellSize, color);

        var cull = document.getElementById("cull");
        cull.onclick = function() {
            applyAutomaton(cells, cellWidth, cellHeight, cellSize,
                           [6, 7, 8], [3, 4, 5, 6, 7, 8]);
            drawCells(cells, cellWidth, cellHeight, cellSize, color);
        };

        var smooth = document.getElementById("smooth");
        smooth.onclick = function() {
            applyAutomaton(cells, cellWidth, cellHeight, cellSize,
                           [5, 6, 7, 8], [5, 6, 7, 8]);
            drawCells(cells, cellWidth, cellHeight, cellSize, color);
        };
    }

    function clearCanvas() {
        var c = document.getElementById("cave");
        var ctx = c.getContext("2d");

        ctx.clearRect(0, 0, c.width, c.height);
    }

    // Builds a 2d array
    function buildArray(cellWidth, cellHeight) {
        var cells = new Array(cellHeight);

        for (var i = 0; i < cellHeight; i++) {
            cells[i] = new Array(cellWidth);

            // Set all values to zero
            for (j = 0; j < cellWidth; j++)
                cells[i][j] = 0;
        }

        return cells;
    }

    function randomizeCells(cells, cellWidth, cellHeight) {
        for (var i = 0; i < cellHeight; i++) {
            for (var j = 0; j < cellWidth; j++) {
                var on = Math.random() < 0.50;

                if (i == 0 || i >= cellHeight - 1 || j == 0 || j >= cellWidth - 1) {
                    on = true;
                }

                cells[i][j] = on ? 1 : 0;
            }
        }
    }

    function drawCells(cells, cellWidth, cellHeight, cellSize, color) {
        clearCanvas();

        var c   = document.getElementById("cave");
        var ctx = c.getContext("2d");
        var pixelData = ctx.createImageData(c.width, c.height);

        for (var i = 0; i < cellHeight; i++) {
            for (var j = 0; j < cellWidth; j++) {
                toggleCell(pixelData, j, i, cellSize, cells[i][j], color);
            }
        }

        ctx.putImageData(pixelData, 0, 0);
    }

    function toggleCell(imageData, i, j, cellSize, isOn, color) {
        var x = i * cellSize;
        var y = j * cellSize;

        var rgb = isOn ?
            hsvToRgb(color, 1, 0.1) :
            hsvToRgb(color, 1, Math.random() * 0.1 + 0.9);

        for (var h = 0; h < cellSize; h++) {
            for (var w = 0; w < cellSize; w++) {
                var index = ((x + w) + (y + h) * imageData.width) * 4;
                imageData.data[index + 0] = rgb[0];
                imageData.data[index + 1] = rgb[1];
                imageData.data[index + 2] = rgb[2];
                imageData.data[index + 3] = 255;
            }
        }
    }

    function applyAutomaton(cells, cellWidth, cellHeight, cellSize, bornList, surviveList) {
        var newCells = buildArray(cellWidth, cellHeight);

        for (var i = 0; i < cellHeight; i++) {
            for (var j = 0; j < cellWidth; j++) {
                var liveCondition;
                if (i == 0 || i >= cellHeight - 1 || j == 0 || j >= cellWidth - 1) {
                    liveCondition = true;
                } else {
                    // Build list of all adjacent cells.
                    var nbhd = 0;
                    nbhd += cells[i-1][j-1];
                    nbhd += cells[i-1][j];
                    nbhd += cells[i-1][j+1];
                    nbhd += cells[i][j-1];
                    nbhd += cells[i][j+1];
                    nbhd += cells[i+1][j-1];
                    nbhd += cells[i+1][j];
                    nbhd += cells[i+1][j+1];

                    var currentState = cells[i][j];
                    var liveCondition =
                        (currentState == 0 && bornList.indexOf(nbhd) > -1)||
                        (currentState == 1 && surviveList.indexOf(nbhd) > -1);
                }
                newCells[i][j] = liveCondition ? 1 : 0;
            }
        }
        for (var i = 0; i < cellHeight; i++) {
            for (var j = 0; j < cellWidth; j++) {
                cells[i][j] = newCells[i][j];
            }
        }
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
