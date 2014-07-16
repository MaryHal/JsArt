(function () {
    var SC_W = 300;
    var SC_H = 400;
    var Scene = function() {
        var c = document.getElementById("bullet");
        c.width = SC_W;
        c.height = SC_H;
        c.style.border = "2px solid #333333";

        this.context = c.getContext("2d");
        this.context.clearRect(0, 0, c.width, c.height);
        this.context.textAlign = "right";
        this.context.textBaseline = "top";

        this.sceneObjects = [];
    };

    // function clearCanvas() {
    //     var c = document.getElementById("cave");
    //     var ctx = c.getContext("2d");

    //     ctx.clearRect(0, 0, c.width, c.height);
    // }

    Scene.prototype.start = function() {
        var renderFrame = function() {
            this.context.fillStyle = "black";
            this.context.globalCompositeOperation = "source-over";
            this.context.fillRect(0, 0, SC_W, SC_H);

            this.context.globalCompositeOperation = "lighter";
            var copied = [].concat(this.sceneObjects);
            for (var i = 0, end = copied.length; i < end; i++) {
                copied[i].update(this.frame);
                copied[i].draw(this.context);
            }

            this.context.fillStyle = "white";

            this.frame += 1;
            requestAnimationFrame(renderFrame);
        }.bind(this);
        renderFrame();
    };
    Scene.prototype.addChild = function(obj) {
        obj.parent = this;
        this.sceneObjects.push(obj);
    };
    Scene.prototype.removeChild = function(obj) {
        obj.parent = null;
        this.sceneObjects.erase(obj);
    };

    var Hex = function(w, h, radius, color) {
        this.radius = radius;
        this.x = 0;
        this.y = 0;
        this.color = color || "hsl(0, 60%, 80%)";

        this.canvas = document.createElement("canvas");
        this.canvas.width = w*2;
        this.canvas.height = h*2;

        var context = this.canvas.getContext("2d");
        context.globalCompositeOperation = "lighter";
        context.fillStyle = this.color;
        context.translate(w, h);
        context.globalAlpha = 1.0;
        context.fillHex(w, h);

        this.parent = null;
    };
    Hex.prototype = {
        constructor: Hex,
        update: function() {},
        draw: function(context) {
            context.fillStyle = this.color;
            context.save();
            context.translate(this.x, this.y);
            context.drawImage(this.canvas, -this.canvas.width*.5, -this.canvas.height*.5);
            context.restore();
        },
        addTo: function(parent) {
            parent.addChild(this);
            return this;
        },
        remove: function() {
            if (this.parent) this.parent.removeChild(this);
            return this;
        }
    };

    /** 敵弾クラス */
    var Bullet = function(spec) {
        Hex.call(this, 8, 8, 2, spec.color);
    };
    Bullet.prototype = Object.create(Hex.prototype);
    Bullet.prototype.areaTest = function() {
        if (this.x < 0 || SC_W < this.x || this.y < 0 || SC_H < this.y) {
            this.remove();
            return;
        }
        };

        /** 自機クラス */
        var Player = function() {
            Hex.call(this, 10, 10, 5, "hsl(120, 60%, 80%)");

            this.x = SC_W * 0.5;
            this.y = SC_H * 0.9;
            this.speed = 1.5;
        };
        Player.prototype = Object.create(Hex.prototype);
        Player.prototype.update = function(frame) {
            // if (keyboard.left) this.x -= this.speed;
            // else if (keyboard.right) this.x += this.speed;
            // if (keyboard.up) this.y -= this.speed;
            // else if (keyboard.down) this.y += this.speed;

            this.x = Math.max(0, Math.min(this.x, SC_W));
            this.y = Math.max(0, Math.min(this.y, SC_H));
        };

        /** キーボード */
        // var keyboard = {
        //     up: false,
        //     down: false,
        //     left: false,
        //     right: false,
        // };
        // document.addEventListener("keydown", function(e) {
        //     switch (e.keyCode) {
        //     case 37: keyboard.left = true; break;
        //     case 38: keyboard.up = true; break;
        //     case 39: keyboard.right = true; break;
        //     case 40: keyboard.down = true; break;
        //     }
        // }, false);
        // document.addEventListener("keyup", function(e) {
        //     switch (e.keyCode) {
        //     case 37: keyboard.left = false; break;
        //     case 38: keyboard.up = false; break;
        //     case 39: keyboard.right = false; break;
        //     case 40: keyboard.down = false; break;
        //     }
        // }, false);

        Array.prototype.erase = function(obj) {
            var idx = this.indexOf(obj);
            if (idx !== -1) this.splice(idx, 1);
        };
        CanvasRenderingContext2D.prototype.fillHex = function(w, h) {
            this.beginPath();
            this.moveTo(Math.sin(Math.PI/3 * 0)*w*.5, Math.cos(Math.PI/3 * 0)*h*.5);
            for (var i = 1; i < 6; i++) {
                this.lineTo(Math.sin(Math.PI/3 * i)*w*.5, Math.cos(Math.PI/3 * i)*h*.5);
            }
            this.closePath();
            this.fill();
        };
        HTMLCanvasElement.prototype.fitWindow = function() {
            var resize = function() {
                var rateWidth = this.width/window.innerWidth;
                var rateHeight= this.height/window.innerHeight;
                var rate = this.height/this.width;
                if (rateWidth > rateHeight) {
                    this.style.width  = innerWidth+"px";
                    this.style.height = innerWidth*rate+"px";
                } else {
                    this.style.width  = innerHeight/rate+"px";
                    this.style.height = innerHeight+"px";
                }
            }.bind(this);
            window.addEventListener("resize", resize, false);
            resize();
        };

        window.onload = function () {
            var scene = new Scene();

            var player = new Player().addTo(scene);

            var danmakuConfig = {
                rank : 1,
                target: player,
                createNewBullet: function(runner, spec) {

                    var bullet = new Bullet(spec);
                    bullet.x = runner.x;
                    bullet.y = runner.y;

                    runner.onVanish = function() {
                        bullet.remove();
                    };

                    bullet.update = function() {
                        runner.update();

                        this.x = runner.x;
                        this.y = runner.y;

                        this.areaTest();
                    };

                    bullet.addTo(scene);
                }
            };

            var filepath = "./pattern/hunsui.bml";
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", filepath, false);
            xmlhttp.send(null);

            var danmaku0 = bulletml.buildXML(xmlhttp.responseText);

            var enemyXML = new Hex(15, 15, 15, "hsl(290, 60%, 80%)").addTo(scene);
            enemyXML.danmakuRunner = danmaku0.createRunner(danmakuConfig);
            enemyXML.update = function(frame) {
                this.x = SC_W / 2;
                this.y = SC_W / 3;
                this.danmakuRunner.x = this.x;
                this.danmakuRunner.y = this.y;
                this.danmakuRunner.update();
            };

            scene.start();
    };
})();

