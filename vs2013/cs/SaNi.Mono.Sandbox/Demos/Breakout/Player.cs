﻿using SaNi.Mono.Engine;
using SaNi.Mono.Graphics.Renderables;
using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Sandbox.Demos.Breakout
{
    /*
        As the engine is still missing the ECS and behaviour scripts for
        entities, we just create wrapper classes around components to
        simulate that.
    */

    public sealed class Player
    {
        #region Properties
        /// <summary>
        /// Visible part of the player. 
        /// Can be used to check collisions 
        /// as well.
        /// </summary>
        public Rectangle Rect
        {
            get;
            private set;
        }
        /// <summary>
        /// Velocity of our player. Default is 1.0f.
        /// </summary>
        public Vector2 Velocity
        {
            get;
            set;
        }
        #endregion

        /// <summary>
        /// Creates new player.
        /// </summary>
        /// <param name="position">start position of the player</param>
        /// <param name="size">size of the player (the paddle)</param>
        public Player(Vector2 position, Vector2 size)
        {
            // Init rect and vel.
            Rect        = new Rectangle(position, size);
            Velocity    = new Vector2(1.0f);
        }

        private Vector2 GetDirectionFromInput()
        {
            if      (Keyboard.IsKeyDown(Keyboard.Key.A)) return new Vector2(-1.0f);
            else if (Keyboard.IsKeyDown(Keyboard.Key.D)) return new Vector2(1.0f);
            else                                         return Vector2.Zero;
        }

        private void Move(Vector2 direction, float delta)
        {
            // "Capture" current transform.
            var transform = Rect.Transform;

            // Apply all changes.
            transform.position.x += delta * Velocity.x * direction.x;
            
            // Apply all changes.
            Rect.Transform = transform;
        }

        public void Update(EngineTime time)
        {
            var direction = GetDirectionFromInput();

            Move(direction, (float)time.FrameTime.TotalMilliseconds);
        }
    }
}
