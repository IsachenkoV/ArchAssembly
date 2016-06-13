using System;
using System.IO;
using Autofac;
using Caliburn.Micro.Autofac;
using GUIdiploma.ViewModels;

namespace GUIdiploma
{
    class AppBootstrapper : AutofacBootstrapper<MainViewModel>
    {
        protected override void ConfigureContainer(ContainerBuilder builder)
        {
            base.ConfigureContainer(builder);
            builder.RegisterType<MainViewModel>().AsSelf().SingleInstance();
        }
    }
}
