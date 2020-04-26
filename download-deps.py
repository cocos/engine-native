#!/usr/bin/env python
#coding=utf-8
#
# ./download-deps.py
#
# Downloads Cocos2D-x 3rd party dependencies from github:
# https://github.com/WenhaiLin/cocos2d-x-lite-external) and extracts the zip
# file
#
# Having the dependencies outside the official cocos2d-x repo helps prevent
# bloating the repo.
#

"""****************************************************************************
Copyright (c) 2014 cocos2d-x.org
Copyright (c) 2014-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************"""

import os.path
import zipfile
import shutil
import sys
import traceback
import distutils
import fileinput
import json
import socket
import urlparse
import select

from optparse import OptionParser
from time import time
from sys import stdout
from distutils.errors import DistutilsError
from distutils.dir_util import copy_tree, remove_tree


def delete_folder_except(folder_path, excepts):
    """
    Delete a folder excepts some files/subfolders, `excepts` doesn't recursively which means it can not include
    `subfoler/file1`. `excepts` is an array.
    """
    for file in os.listdir(folder_path):
        if (file in excepts):
            continue

        full_path = os.path.join(folder_path, file)
        if os.path.isdir(full_path):
            shutil.rmtree(full_path)
        else:
            os.remove(full_path)


def connect_by_url(uri):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.setblocking(0) # make non-blocking
    url = urlparse.urlparse(uri)
    scheme = url.scheme
    hostname = url.hostname
    port = url.port
    if port is None:
        if scheme == "https":
            port = 443
        else:
            port = 80
    print("==>  Connecting %s:%s" %(hostname, port))
    try:
        client.connect_ex((hostname, port))
    except Exception as e:
        print("[error] connect %s" % e)
        return None
    return client

def select_fastest_url(url_list):
    clients = filter(None, [connect_by_url(url) for url in url_list])
    writable_sockets =  clients[:]
    # ping servers
    t1 = time()
    sorted_list = []
    while len(writable_sockets) > 0:
        ready_to_read, ready_to_write, in_error = select.select(
            [], writable_sockets, writable_sockets, 5.0)
        t2 = time()
        for socket in ready_to_write:
            index = clients.index(socket)
            url = url_list[index]
            sorted_list.append(url)
            print("==>   Takes %ss to connect to #%s" % (t2 - t1, index))
            writable_sockets.remove(socket)
        for socket in in_error:
            writable_sockets.remove(socket)

        if len(ready_to_read) == 0 and len(ready_to_write) == 0 and len(in_error):
            print("[error] timeout occurs!")

    # close all tcp connections
    for i in clients:
        try:
            i.close()
        except:
            pass
        
    # skip if url is 404 or other errors
    import urllib2
    for url in sorted_list:
        u = None
        try:
            print("==>   Try fetch %s" % url)
            u = urllib2.urlopen(url)
            print("==>     Response code: %s " % u.getcode())
            return url
        except urllib2.HTTPError as e:
            print("==>     Http request failed, error code: " + str(e.code))
        finally:
            if u is not None:
                u.close()
    # fallback case 
    if len(sorted_list) == 0:
        return url_list[0]


class UnrecognizedFormat:
    def __init__(self, prompt):
        self._prompt = prompt

    def __str__(self):
        return self._prompt


class CocosZipInstaller(object):
    def __init__(self, workpath, config_path, version_path, remote_version_key, mirror):
        self._workpath = workpath
        self._config_path = config_path
        self._version_path = version_path

        data = self.load_json_file(config_path)

        self._current_version = data["version"]
        self._repo_name = data["repo_name"]
        try:
            self._move_dirs = data["move_dirs"]
        except:
            self._move_dirs = None
        self._filename = self._current_version + '.zip'
        self._url = data["repo_parent"] + self._repo_name + '/archive/' + self._filename
        self._zip_file_size = int(data["zip_file_size"])
        # 'v' letter was swallowed by github, so we need to substring it from the 2nd letter
        self._extracted_folder_name = os.path.join(self._workpath, self._repo_name + '-' + self._current_version[1:])
        
        mirror_repo_url = "http://gitlab.cocos.net:8929/publics/%s/-/archive/%s/%s-%s.zip" % (self._repo_name, self._current_version, self._repo_name, self._current_version)
        if mirror is None:
            self._url = select_fastest_url([self._url, mirror_repo_url])
        elif mirror == "gitlab":
            self._url = mirror_repo_url
        
        try:
            data = self.load_json_file(version_path)
            if remote_version_key is None:
                self._remote_version = data["version"]
            else:
                self._remote_version = data[remote_version_key]
        except:
            print("==> version file doesn't exist")

    def get_input_value(self, prompt):
        ret = raw_input(prompt)
        ret.rstrip(" \t")
        return ret

    def download_file(self):
        print("==> Ready to download '%s' from '%s'" % (self._filename, self._url))
        import urllib2
        try:
            u = urllib2.urlopen(self._url)
        except urllib2.HTTPError as e:
            if e.code == 404:
                print("==> Error: Could not find the file from url: '%s'" % (self._url))
            print("==> Http request failed, error code: " + str(e.code) + ", reason: " + e.read())
            sys.exit(1)

        # record previous download url
        script_dir = os.path.dirname(os.path.realpath(__file__))
        download_url = os.path.join(script_dir, "external", ".download_link")
        line = ""
        if os.path.exists(download_url):
            fo = open(download_url, "rt")
            # read previous url
            line = fo.readline()
            fo.close()
            # if downloaded from different url, remove the file
            if line.strip() != self._url and os.path.exists(self._filename):
                print("==> Url has changed, delete previous file %s" % self._filename)
                os.remove(self._filename)

        fw = open(download_url, 'wt')
        fw.write(self._url+"\n")
        fw.close()

        f = open(self._filename, 'wb')
        meta = u.info()
        content_len = meta.getheaders("Content-Length")
        file_size = 0
        if content_len and len(content_len) > 0:
            file_size = int(content_len[0])
        else:
            # github server may not reponse a header information which contains `Content-Length`,
            # therefore, the size needs to be written hardcode here. While server doesn't return
            # `Content-Length`, use it instead
            print("==> WARNING: Couldn't grab the file size from remote, use 'zip_file_size' section in '%s'" % self._config_path)
            file_size = self._zip_file_size

        print("==> Start to download, please wait ...")

        file_size_dl = 0
        block_sz = 8192
        block_size_per_second = 0
        old_time = time()

        status = ""
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                print("%s%s" % (" " * len(status), "\r")),
                break

            file_size_dl += len(buffer)
            block_size_per_second += len(buffer)
            f.write(buffer)
            new_time = time()
            if (new_time - old_time) > 1:
                speed = block_size_per_second / (new_time - old_time) / 1000.0
                if file_size != 0:
                    percent = file_size_dl * 100. / file_size
                    status = r"Downloaded: %6dK / Total: %dK, Percent: %3.2f%%, Speed: %6.2f KB/S " % (file_size_dl / 1000, file_size / 1000, percent, speed)
                else:
                    status = r"Downloaded: %6dK, Speed: %6.2f KB/S " % (file_size_dl / 1000, speed)
                print(status),
                sys.stdout.flush()
                print("\r"),
                block_size_per_second = 0
                old_time = new_time

        print("==> Downloading finished!")
        f.close()

    def ensure_directory(self, target):
        if not os.path.exists(target):
            os.mkdir(target)

    def unpack_zipfile(self, extract_dir):
        """Unpack zip `filename` to `extract_dir`

        Raises ``UnrecognizedFormat`` if `filename` is not a zipfile (as determined
        by ``zipfile.is_zipfile()``).
        """

        if not zipfile.is_zipfile(self._filename):
            raise UnrecognizedFormat("%s is not a zip file" % (self._filename))

        print("==> Extracting files, please wait ...")
        z = zipfile.ZipFile(self._filename)
        try:
            for info in z.infolist():
                name = info.filename

                # don't extract absolute paths or ones with .. in them
                if name.startswith('/') or '..' in name:
                    continue

                # anchor file, may change
                if name.endswith("versions.txt"):
                    self._extracted_folder_name = os.path.basename(os.path.dirname(name))
                   
                target = os.path.join(extract_dir, *name.split('/'))
                if not target:
                    continue
                if name.endswith('/'):
                    # directory
                    self.ensure_directory(target)
                else:
                    # file
                    data = z.read(info.filename)
                    f = open(target, 'wb')
                    try:
                        f.write(data)
                    finally:
                        f.close()
                        del data
                unix_attributes = info.external_attr >> 16
                if unix_attributes:
                    os.chmod(target, unix_attributes)
        finally:
            z.close()
            print("==> Extraction done!")

    def ask_to_delete_downloaded_zip_file(self):
        ret = self.get_input_value("==> Would you like to save '%s'? So you don't have to download it later. [yes/no]: " % self._filename)
        ret = ret.strip()
        if ret != 'yes' and ret != 'y' and ret != 'no' and ret != 'n':
            print("==> Saving the dependency libraries by default")
            return False
        else:
            return True if ret == 'no' or ret == 'n' else False

    def download_zip_file(self):
        if not os.path.isfile(self._filename):
            self.download_file()
        try:
            if not zipfile.is_zipfile(self._filename):
                raise UnrecognizedFormat("%s is not a zip file" % (self._filename))
        except UnrecognizedFormat as e:
            print("==> Unrecognized zip format from your local '%s' file!" % (self._filename))
            if os.path.isfile(self._filename):
                os.remove(self._filename)
            print("==> Download it from internet again, please wait...")
            self.download_zip_file()

    def need_to_update(self):
        if not os.path.isfile(self._version_path):
            return True

        with open(self._version_path) as data_file:
            data = json.load(data_file)

        if self._remote_version == self._current_version:
            return False
        return True

    def load_json_file(self, file_path):
        if not os.path.isfile(file_path):
            raise Exception("Could not find (%s)" % (file_path))

        with open(file_path) as data_file:
            data = json.load(data_file)
        return data

    def clean_external_folder(self, external_folder):
        print('==> Cleaning cocos2d-x/external folder ...')
        # remove external except 'config.json'
        delete_folder_except(external_folder, ['config.json'])

    def run(self, workpath, folder_for_extracting, remove_downloaded, force_update, download_only):
        if not force_update and not self.need_to_update():
            print("==> Not need to update!")
            return

        if os.path.exists(self._extracted_folder_name):
            shutil.rmtree(self._extracted_folder_name)

        self.download_zip_file()

        if not download_only:
            self.unpack_zipfile(self._workpath)

            if not os.path.exists(folder_for_extracting):
                os.mkdir(folder_for_extracting)

            self.clean_external_folder(folder_for_extracting)
            print("==> Copying files...")
            distutils.dir_util.copy_tree(self._extracted_folder_name, folder_for_extracting)
            if self._move_dirs is not None:
                for srcDir in self._move_dirs.keys():
                    distDir = os.path.join( os.path.join(workpath, self._move_dirs[srcDir]), srcDir)
                    if os.path.exists(distDir):
                        shutil.rmtree(distDir)
                    shutil.move( os.path.join(folder_for_extracting, srcDir), distDir)
            print("==> Cleaning...")
            if os.path.exists(self._extracted_folder_name):
                shutil.rmtree(self._extracted_folder_name)
            if os.path.isfile(self._filename):
                if remove_downloaded is not None:
                    if remove_downloaded == 'yes':
                        os.remove(self._filename)
                elif self.ask_to_delete_downloaded_zip_file():
                    os.remove(self._filename)
        else:
            print("==> Download (%s) finish!" % self._filename)


def _check_python_version():
    major_ver = sys.version_info[0]
    if major_ver > 2:
        print ("The python version is %d.%d. But python 2.x is required. (Version 2.7 is well tested)\n"
               "Download it here: https://www.python.org/" % (major_ver, sys.version_info[1]))
        return False

    return True


def main():
    workpath = os.path.dirname(os.path.realpath(__file__))

    if not _check_python_version():
        exit()

    parser = OptionParser()
    parser.add_option('-r', '--remove-download',
                      action="store", type="string", dest='remove_downloaded', default=None,
                      help="Whether to remove downloaded zip file, 'yes' or 'no'")

    parser.add_option("-f", "--force-update",
                      action="store_true", dest="force_update", default=False,
                      help="Whether to force update the third party libraries")

    parser.add_option("-d", "--download-only",
                      action="store_true", dest="download_only", default=False,
                      help="Only download zip file of the third party libraries, will not extract it")

    parser.add_option("--github", 
                     action="store_true", dest="from_github", default=False,
                     help="Download zip from github.com" )

    parser.add_option("--gitlab", 
                     action="store_true", dest="from_gitlab", default=False,
                     help="Download zip from gitlab.cocos.net" )

    (opts, args) = parser.parse_args()

    mirror = None
    if opts.from_github:
        mirror = "github"
    if opts.from_gitlab:
        mirror = "gitlab"

    print("=======================================================")
    print("==> Prepare to download external libraries!")
    external_path = os.path.join(workpath, 'external')
    installer = CocosZipInstaller(workpath, os.path.join(workpath, 'external', 'config.json'), os.path.join(workpath, 'external', 'version.json'), "prebuilt_libs_version", mirror)
    installer.run(workpath, external_path, opts.remove_downloaded, opts.force_update, opts.download_only)

# -------------- main --------------
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
