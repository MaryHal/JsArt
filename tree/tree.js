(function () {
    // Timing
    var timer = null;
    var interval = 15;

    // Node handling
    var root = null;
    var nodes = [];

    // Customization
    var initialWidth = 8;
    var leafRadius = 1.5;

    // Initial Values
    var u0 = 440;
    var grow_t = 0.1;
    var branch_d = 0.85;
    var branch_t = 0.5;

    var ctx = null;

    // Node Struct
    function TreeNode() {
        this.parent = null;
        this.root = null;
        this.hue = 0;
        this.origin = [0, 0];
        this.r = 0.0;
        this.u = 0.0;
        this.v = 0;
        this.old_r = this.r;
        this.old_u = this.u;
    }


    window.onload = function() {
        // Set Canvas
        var c = document.getElementById("tree");
        c.width = 320;
        c.height = 400;
        c.style.border = "2px solid #333333";

        // Center Canvas
        c.style.display = "block";
        c.style.marginTop   = "0";
        c.style.marginLeft  = "auto";
        c.style.marginRight = "auto";

        // Center buttons
        var buttonContainer = document.getElementById("buttonContainer");
        buttonContainer.style.textAlign = "center";

        var start = document.getElementById("start");
        start.onclick = run;
    };

    function run() {
        if (timer != null)
            return;

        // Setup our rendering context
        var c = document.getElementById("tree");
        ctx = c.getContext("2d");
        clearCanvas();

        // Draw Ground
        ctx.lineWidth = 1;
        ctx.strokeStyle = 'rgb(30, 10, 15)';
        ctx.beginPath();
        ctx.moveTo(0, 320);
        ctx.lineTo(320, 320);
        ctx.stroke();

        // Reset
        root = null;
        nodes = [];

        // Setup root node
        root = new TreeNode();
        root.parent = root;
        root.root = root;
        root.u = u0;
        root.old_u = root.u;
        root.origin = [160, 320];
        root.hue = Math.random() * 255;

        nodes.push(root);

        timer = setInterval(growTree, interval);
    }

    function growTree() {
        for (var i = nodes.length - 1; i >= 0; i--)
        {
            var current = nodes[i];

            var child = new TreeNode();
            child.parent = current;
            child.root = current.root;
            child.hue = child.parent.hue + ((Math.random() * 10) - 5);
            child.v = current.v + 1;
            child.r = (current.old_r + (current.r + ((Math.random() * grow_t) - (grow_t / 2)))) / 2;
            child.u = current.u - (Math.random() + 1);
            child.old_u = current.old_u;
            child.old_r = current.r;

            child.origin = [current.origin[0] + Math.sin(child.r + Math.PI),
                            current.origin[1] + Math.cos(child.r + Math.PI)];

            drawNode(child);

            if (child.u <= 0)
            {
                drawLeaf(child);
                nodes.splice(i, 1);
                continue;
            }

            nodes[i] = child;

            // branch
            if (child.v >= 10 && Math.random() > branch_d && Math.random() > 1 - ((u0 - child.u) / u0))
            {
                branch = new TreeNode();
                branch.parent = child;
                branch.root = child.root;
                branch.hue = branch.parent.hue + ((Math.random() * 20) - 10);
                branch.v = child.v;
                branch.r = child.r + (Math.random() > 0.5 ? Math.PI / 2 : -1 * Math.PI / 2) + ((Math.random() * branch_t) - (branch_t / 2));
                branch.r = (branch.r + (child.r * (Math.random() * 0.5) + 0.5)) / 2;
                branch.u = child.u * (Math.random() * 0.8);
                branch.old_u = branch.u;
                branch.old_r = branch.r;

                branch.origin = [child.origin[0] + Math.sin(child.r + Math.PI),
                                 child.origin[1] + Math.cos(child.r + Math.PI)];
                drawNode(branch);

                nodes.push(branch);
            }
        }

        if (nodes.length == 0)
        {
            clearTimeout(timer);
            timer = null;
        }
    }

    function drawNode(node) {
        ctx.lineWidth = (node.u / u0) * initialWidth;

        // Bound line width
        if (ctx.lineWidth < 1)
        {
            ctx.lineWidth = 1;
        }

        ctx.strokeStyle = 'rgb(60, 20, 30)';
        ctx.beginPath();
        ctx.moveTo(node.parent.origin[0], node.parent.origin[1]);
        ctx.lineTo(node.origin[0], node.origin[1]);
        ctx.stroke();
    }

    function drawLeaf(node) {
        ctx.fillStyle = 'hsl(' + node.hue + ', 100%, 50%)';
        ctx.arc(node.origin[0], node.origin[1], leafRadius, 0, Math.PI * 2);
        ctx.fill();
    }

    function clearCanvas() {
        if (ctx != null)
        {
            var c = document.getElementById("tree");
            ctx.clearRect(0, 0, c.width, c.height);
        }
    }
})();
