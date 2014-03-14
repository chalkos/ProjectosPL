# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  # Every Vagrant virtual environment requires a box to build off of.
  config.vm.box = "chef/ubuntu-13.10"

  config.vm.provision "shell", path: "https://gist.githubusercontent.com/chalkos/9d90276f504a8fc2cdd5/raw/d969c1bf54bba12124ebd74540bc1ee540260af2/vagrant_ubuntu_pl.sh"
end
