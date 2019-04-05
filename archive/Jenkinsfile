pipeline {
    agent {
        docker { image 'debian:stretch' }
    }
    stages {
        stage('Dependencies') {
            steps {
                sh '''
                    set -e

                    apt-get update
                    apt-get install -y git build-essential cmake

                    git clone --depth=1 git://git.drogon.net/wiringPi
                    cd wiringPi/wiringPi
                    make
                    make install
                '''
            }
        }
        stage('Build') {
            steps {
                sh '''
                    set -e

                    cd brain
                    mkdir build
                    cd build
                    cmake ..
                    make
                '''
            }
        }
    }
    post {
        always {
            cleanWs()
        }
    }
}
