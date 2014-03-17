# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  # Every Vagrant virtual environment requires a box to build off of.
  config.vm.box = "chef/ubuntu-13.10"

  config.vm.synced_folder "./", "/vagrant", mount_options: ["dmode=775,fmode=775"]

  config.vm.provision "shell", path: "Vagrantprovision"
end
