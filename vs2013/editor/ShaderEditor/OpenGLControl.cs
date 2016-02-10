﻿using ShaderEditor.GL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ShaderEditor
{
    internal sealed class OpenGLControl : UserControl
    {
        #region Const fields
        public int MaxFps = 0;
        #endregion

        #region Fields
        private readonly Stopwatch renderTimeMeasurer;
        private readonly Timer renderTimer;

        private int preferedFPS;
        private double frameTime;
        #endregion 

        #region Properties
        /// <summary>
        /// Sets the prefered FPS. Setting the value to 0 or 
        /// using the MaxFPS const causes the control
        /// to render with no FPS limit.
        /// </summary>
        public int PreferedFPS
        {
            get
            {
                return preferedFPS;
            }
            set
            {
                this.preferedFPS = value;

                SetupRenderingTimer();
            }
        }
        public int FPS
        {
            get
            {
                return (int)(1000.0 / frameTime);
            }
        }
        #endregion

        #region Events
        public event InitializeEventHandler OpenGLInitialized;
        public event RenderEventHandler OpenGLRender;
        #endregion

        public OpenGLControl()
            : base()
        {
            DoubleBuffered = false;

            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.UserPaint, true);

            renderTimeMeasurer = new Stopwatch();
            renderTimer = new Timer();

            PreferedFPS = 60;
        }

        #region Event handler
        private void renderTimer_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }
        #endregion

        private void Render(Graphics graphics)
        {
            renderTimeMeasurer.Restart();

            // Allow user to draw using OpenGL.
            if (OpenGLRender != null) OpenGLRender(this, RenderingEventArgs.Empty);

            // Draw.
            IntPtr handleDeviceContext = graphics.GetHdc();

            OpenGL.SwapBuffers((uint)handleDeviceContext);

            graphics.ReleaseHdc(handleDeviceContext);

            renderTimeMeasurer.Stop();

            this.frameTime = renderTimeMeasurer.Elapsed.TotalMilliseconds;
        }

        private void SetupRenderingTimer()
        {
            int interval = (int)(1000.0 / (double)PreferedFPS);
            interval = interval == 0 ? 1 : interval;

            renderTimer.Interval = interval;

            if (!renderTimer.Enabled)
            {
                renderTimer.Tick += renderTimer_Tick;
                renderTimer.Enabled = true;

                renderTimer.Start();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            this.Render(e.Graphics);
        }
        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // Do an empty override as this causes flickering...
        }
        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);

            OpenGL.GLViewport(0, 0, (uint)Width, (uint)Height);

            Invalidate();
        }

        public void InitializeOpenGL()
        {
            IntPtr handle = this.Handle;

            OpenGL.CreateContext(handle);
            OpenGL.GLEnable(GL_ENUMS.GL_BLEND);
            OpenGL.GLBlendFunc(GL_ENUMS.GL_SRC_ALPHA, GL_ENUMS.GL_ONE_MINUS_SRC_ALPHA);
            
            if (OpenGLInitialized != null) OpenGLInitialized(this, InitializationEventArgs.Empty);
        }
        public void StartRendering()
        {
            SetupRenderingTimer();
        }
    }
}
